---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:37:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 71-96 cores)</summary>

```
1794508142 94
1794508147 94
1794508152 96
1794508157 96
1794508162 96
1794508167 96
1794508172 96
1794508177 96
1794508182 96
1794508187 96
1794508192 96
1794508197 96
1794508202 96
1794508207 96
1794508212 96
1794508217 96
1794508222 96
1794508227 96
1794508232 91
1794508237 91
```
</details>

---

