---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:01:50 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1792670213 88
1792670218 88
1792670223 88
1792670228 88
1792670233 88
1792670238 96
1792670243 96
1792670248 96
1792670253 96
1792670258 96
1792670263 96
1792670268 96
1792670273 96
1792670278 96
1792670283 96
1792670288 96
1792670293 96
1792670298 96
1792670303 96
1792670308 96
```
</details>

---

