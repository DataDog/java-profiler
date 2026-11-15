---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 08:56:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794750696 81
1794750701 79
1794750706 79
1794750711 79
1794750716 79
1794750721 81
1794750726 81
1794750731 81
1794750736 81
1794750741 81
1794750746 81
1794750751 81
1794750756 81
1794750761 81
1794750766 81
1794750771 81
1794750776 81
1794750781 81
1794750786 81
1794750791 81
```
</details>

---

