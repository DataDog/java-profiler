---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-11 19:24:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 12.38/sec |
| Health Score | 774% |
| Threads | 12 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1778541639 93
1778541644 93
1778541649 93
1778541654 93
1778541659 93
1778541664 91
1778541669 91
1778541674 91
1778541679 91
1778541684 91
1778541689 91
1778541694 91
1778541699 91
1778541704 91
1778541709 91
1778541714 91
1778541720 91
1778541725 91
1778541730 91
1778541735 91
```
</details>

---

