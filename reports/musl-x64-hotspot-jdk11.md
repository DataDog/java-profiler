---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 11:39:43 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 13.62/sec |
| Health Score | 851% |
| Threads | 11 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1794328302 74
1794328307 74
1794328312 74
1794328317 74
1794328322 74
1794328327 74
1794328332 74
1794328337 74
1794328342 74
1794328347 74
1794328352 74
1794328357 74
1794328362 74
1794328367 74
1794328372 74
1794328377 72
1794328382 72
1794328387 72
1794328392 72
1794328397 72
```
</details>

---

