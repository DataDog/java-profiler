---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 09:29:53 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 56-65 cores)</summary>

```
1795098282 56
1795098287 56
1795098292 56
1795098297 56
1795098302 56
1795098307 56
1795098312 56
1795098317 56
1795098322 56
1795098327 56
1795098332 65
1795098337 65
1795098342 60
1795098347 60
1795098352 60
1795098357 60
1795098362 60
1795098367 60
1795098372 60
1795098377 60
```
</details>

---

