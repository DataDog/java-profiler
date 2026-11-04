---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 16:24:56 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (5 unique values: 49-67 cores)</summary>

```
1793827182 49
1793827187 49
1793827192 49
1793827197 52
1793827202 52
1793827207 50
1793827213 50
1793827218 50
1793827223 50
1793827228 50
1793827233 50
1793827238 50
1793827243 50
1793827248 50
1793827253 50
1793827258 65
1793827263 65
1793827268 65
1793827273 65
1793827278 65
```
</details>

---

