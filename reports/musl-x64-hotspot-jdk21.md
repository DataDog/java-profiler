---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-24 17:04:00 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 8 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 11 |
| Allocations | 155 |

<details>
<summary>CPU Timeline (4 unique values: 69-82 cores)</summary>

```
1777064263 72
1777064268 72
1777064273 72
1777064278 72
1777064283 72
1777064288 72
1777064293 72
1777064298 72
1777064303 72
1777064308 72
1777064313 72
1777064318 72
1777064323 74
1777064328 74
1777064333 69
1777064338 69
1777064343 69
1777064348 82
1777064353 82
1777064358 82
```
</details>

---

