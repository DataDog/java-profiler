---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 13:37:08 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 907 |
| Sample Rate | 15.12/sec |
| Health Score | 945% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 78-80 cores)</summary>

```
1794508151 80
1794508156 80
1794508161 80
1794508167 80
1794508172 80
1794508177 80
1794508182 80
1794508187 80
1794508192 80
1794508197 80
1794508202 78
1794508207 78
1794508212 78
1794508217 78
1794508222 78
1794508227 78
1794508232 78
1794508237 78
1794508242 78
1794508247 78
```
</details>

---

