---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-24 00:57:22 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 12 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 9 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787547189 29
1787547194 29
1787547199 29
1787547204 29
1787547209 34
1787547214 34
1787547219 34
1787547224 34
1787547229 34
1787547234 34
1787547239 34
1787547244 34
1787547249 34
1787547254 34
1787547259 34
1787547264 34
1787547269 34
1787547274 34
1787547279 34
1787547284 34
```
</details>

---

