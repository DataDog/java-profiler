---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 08:56:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 870 |
| Sample Rate | 14.50/sec |
| Health Score | 906% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1794750711 79
1794750716 79
1794750721 81
1794750726 81
1794750731 81
1794750736 81
1794750741 81
1794750746 81
1794750751 81
1794750757 81
1794750762 81
1794750767 81
1794750772 81
1794750777 81
1794750782 81
1794750787 81
1794750792 81
1794750797 81
1794750802 81
1794750807 81
```
</details>

---

