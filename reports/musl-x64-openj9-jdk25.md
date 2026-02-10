---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-10 07:11:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1091 |
| Sample Rate | 18.18/sec |
| Health Score | 1136% |
| Threads | 13 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 25-29 cores)</summary>

```
1770725225 29
1770725230 29
1770725235 29
1770725240 29
1770725245 29
1770725251 29
1770725256 29
1770725261 29
1770725266 29
1770725271 29
1770725276 29
1770725281 29
1770725286 29
1770725291 29
1770725296 25
1770725301 25
1770725306 25
1770725311 25
1770725316 25
1770725321 25
```
</details>

---

