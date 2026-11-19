---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 11:31:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 71-83 cores)</summary>

```
1795105584 83
1795105589 83
1795105594 83
1795105599 83
1795105604 83
1795105609 83
1795105614 83
1795105619 83
1795105624 83
1795105629 83
1795105634 83
1795105639 83
1795105644 83
1795105649 83
1795105654 83
1795105659 83
1795105664 71
1795105669 71
1795105674 71
1795105679 71
```
</details>

---

