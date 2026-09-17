---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 18:00:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 16 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (1 unique values: 33-33 cores)</summary>

```
1789682184 33
1789682189 33
1789682194 33
1789682199 33
1789682204 33
1789682209 33
1789682214 33
1789682219 33
1789682224 33
1789682229 33
1789682234 33
1789682239 33
1789682244 33
1789682249 33
1789682254 33
1789682259 33
1789682264 33
1789682269 33
1789682274 33
1789682279 33
```
</details>

---

