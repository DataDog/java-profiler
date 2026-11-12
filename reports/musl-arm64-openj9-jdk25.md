---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 09:43:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 11 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794494162 51
1794494167 51
1794494172 51
1794494177 51
1794494182 51
1794494187 51
1794494192 51
1794494197 51
1794494202 51
1794494207 51
1794494212 64
1794494217 64
1794494222 64
1794494227 64
1794494232 64
1794494237 64
1794494242 64
1794494247 64
1794494252 64
1794494257 64
```
</details>

---

