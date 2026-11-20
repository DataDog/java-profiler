---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:32:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 28-64 cores)</summary>

```
1795192154 28
1795192159 28
1795192164 28
1795192169 28
1795192174 28
1795192179 28
1795192184 28
1795192189 28
1795192194 28
1795192199 28
1795192204 28
1795192209 28
1795192214 28
1795192219 28
1795192224 28
1795192229 28
1795192234 28
1795192239 28
1795192244 28
1795192249 28
```
</details>

---

