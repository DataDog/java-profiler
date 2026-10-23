---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 19:01:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 64-70 cores)</summary>

```
1792796157 64
1792796162 64
1792796167 64
1792796172 64
1792796177 64
1792796182 64
1792796187 64
1792796192 64
1792796197 64
1792796202 64
1792796207 64
1792796212 64
1792796217 64
1792796222 64
1792796227 64
1792796232 64
1792796237 64
1792796242 64
1792796247 64
1792796252 64
```
</details>

---

