---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 09:57:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795186253 49
1795186258 49
1795186263 49
1795186268 49
1795186273 49
1795186278 49
1795186283 49
1795186288 49
1795186293 49
1795186298 49
1795186303 49
1795186308 49
1795186313 49
1795186318 49
1795186323 49
1795186328 49
1795186333 49
1795186338 44
1795186343 44
1795186348 44
```
</details>

---

