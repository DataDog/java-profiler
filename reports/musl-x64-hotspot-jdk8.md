---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-05 11:50:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 319 |
| Sample Rate | 5.32/sec |
| Health Score | 332% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 22-30 cores)</summary>

```
1791215142 30
1791215147 30
1791215152 30
1791215157 30
1791215162 30
1791215167 30
1791215172 30
1791215177 30
1791215182 30
1791215187 30
1791215192 30
1791215197 30
1791215202 30
1791215207 30
1791215212 30
1791215217 30
1791215222 22
1791215227 22
1791215232 22
1791215237 22
```
</details>

---

