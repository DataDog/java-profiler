---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:35:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 945 |
| Sample Rate | 15.75/sec |
| Health Score | 984% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 76-88 cores)</summary>

```
1794508132 76
1794508137 76
1794508142 76
1794508147 82
1794508152 82
1794508157 82
1794508162 82
1794508167 82
1794508172 82
1794508177 82
1794508182 82
1794508187 88
1794508192 88
1794508197 88
1794508202 88
1794508207 88
1794508212 88
1794508217 88
1794508222 88
1794508227 88
```
</details>

---

