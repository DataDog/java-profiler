---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:18:50 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (4 unique values: 13-23 cores)</summary>

```
1795641201 23
1795641206 23
1795641211 23
1795641216 23
1795641221 23
1795641226 23
1795641231 23
1795641236 23
1795641241 23
1795641246 23
1795641251 23
1795641256 23
1795641261 23
1795641266 23
1795641271 23
1795641276 23
1795641281 15
1795641286 15
1795641291 13
1795641296 13
```
</details>

---

