---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 04:29:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 11 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (2 unique values: 55-63 cores)</summary>

```
1790238267 55
1790238272 55
1790238277 55
1790238282 55
1790238287 55
1790238292 55
1790238297 55
1790238302 55
1790238307 55
1790238312 55
1790238317 55
1790238322 55
1790238327 55
1790238332 55
1790238337 63
1790238342 63
1790238347 63
1790238352 63
1790238357 63
1790238362 63
```
</details>

---

