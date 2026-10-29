---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 17:38:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793309678 30
1793309683 30
1793309688 32
1793309693 32
1793309698 32
1793309703 30
1793309708 30
1793309713 30
1793309718 30
1793309723 30
1793309728 30
1793309733 30
1793309738 30
1793309743 30
1793309748 30
1793309753 30
1793309758 30
1793309763 30
1793309768 30
1793309773 30
```
</details>

---

