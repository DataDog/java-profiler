---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:37:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 11 |
| Allocations | 200 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 42-46 cores)</summary>

```
1794508147 46
1794508152 46
1794508157 42
1794508162 42
1794508167 42
1794508172 42
1794508177 42
1794508182 42
1794508187 44
1794508192 44
1794508197 44
1794508202 44
1794508207 44
1794508212 44
1794508217 44
1794508222 44
1794508227 46
1794508232 46
1794508237 46
1794508242 44
```
</details>

---

