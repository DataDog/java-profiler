---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 07:31:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 10 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 11 |
| Allocations | 563 |

<details>
<summary>CPU Timeline (4 unique values: 58-84 cores)</summary>

```
1790767639 58
1790767644 58
1790767649 58
1790767654 58
1790767659 78
1790767664 78
1790767669 78
1790767674 78
1790767679 78
1790767684 78
1790767689 78
1790767694 78
1790767699 81
1790767704 81
1790767709 81
1790767714 81
1790767719 81
1790767724 81
1790767729 84
1790767734 84
```
</details>

---

