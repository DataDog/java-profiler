---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 11:20:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 8 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (1 unique values: 60-60 cores)</summary>

```
1795796188 60
1795796193 60
1795796198 60
1795796203 60
1795796208 60
1795796213 60
1795796218 60
1795796223 60
1795796228 60
1795796233 60
1795796238 60
1795796243 60
1795796248 60
1795796253 60
1795796258 60
1795796263 60
1795796268 60
1795796273 60
1795796278 60
1795796283 60
```
</details>

---

