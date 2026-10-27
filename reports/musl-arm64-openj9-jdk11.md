---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 09:26:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793107229 48
1793107234 48
1793107239 48
1793107244 48
1793107249 48
1793107254 48
1793107259 48
1793107264 48
1793107269 48
1793107274 48
1793107279 48
1793107284 48
1793107289 48
1793107294 48
1793107299 48
1793107304 48
1793107309 48
1793107314 48
1793107319 48
1793107324 48
```
</details>

---

