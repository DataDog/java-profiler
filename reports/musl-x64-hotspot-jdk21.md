---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:14:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 902 |
| Sample Rate | 15.03/sec |
| Health Score | 939% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1795108184 63
1795108189 63
1795108194 63
1795108199 63
1795108204 63
1795108209 63
1795108214 65
1795108219 65
1795108224 65
1795108230 65
1795108235 65
1795108240 65
1795108245 65
1795108250 65
1795108255 65
1795108260 65
1795108265 65
1795108270 65
1795108275 65
1795108280 65
```
</details>

---

