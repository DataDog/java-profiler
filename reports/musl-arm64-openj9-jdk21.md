---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 08:08:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 11 |
| Allocations | 158 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789992202 48
1789992207 48
1789992212 43
1789992217 43
1789992222 43
1789992227 43
1789992232 43
1789992237 43
1789992242 43
1789992247 43
1789992252 43
1789992257 43
1789992262 48
1789992267 48
1789992272 48
1789992277 48
1789992282 48
1789992287 48
1789992292 48
1789992297 48
```
</details>

---

