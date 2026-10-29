---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 17:38:35 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 57-79 cores)</summary>

```
1793309663 79
1793309668 79
1793309673 79
1793309678 79
1793309683 79
1793309688 79
1793309693 79
1793309698 79
1793309703 77
1793309708 77
1793309713 77
1793309718 77
1793309723 77
1793309728 77
1793309733 75
1793309738 75
1793309743 75
1793309748 75
1793309753 75
1793309758 75
```
</details>

---

