---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:33:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794508077 40
1794508082 40
1794508087 40
1794508092 40
1794508097 40
1794508102 40
1794508107 40
1794508112 40
1794508117 40
1794508122 40
1794508127 40
1794508132 40
1794508137 40
1794508142 40
1794508147 40
1794508152 40
1794508157 40
1794508162 40
1794508167 40
1794508172 40
```
</details>

---

