---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-21 08:39:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 10 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1787315644 36
1787315649 36
1787315654 46
1787315659 46
1787315664 46
1787315669 46
1787315674 46
1787315679 46
1787315684 48
1787315689 48
1787315694 48
1787315699 48
1787315704 48
1787315709 48
1787315714 48
1787315719 48
1787315724 48
1787315729 48
1787315734 48
1787315739 48
```
</details>

---

