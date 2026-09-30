---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 07:31:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 974 |
| Sample Rate | 16.23/sec |
| Health Score | 1014% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 33-41 cores)</summary>

```
1790767629 41
1790767634 41
1790767639 41
1790767644 41
1790767649 41
1790767654 41
1790767659 41
1790767664 41
1790767669 41
1790767674 41
1790767679 41
1790767684 33
1790767689 33
1790767694 33
1790767699 33
1790767704 33
1790767709 33
1790767714 33
1790767719 33
1790767724 33
```
</details>

---

