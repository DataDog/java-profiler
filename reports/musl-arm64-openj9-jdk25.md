---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 17:08:40 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 163 |
| Sample Rate | 2.72/sec |
| Health Score | 170% |
| Threads | 10 |
| Allocations | 100 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 22-35 cores)</summary>

```
1794348231 22
1794348236 22
1794348241 22
1794348246 22
1794348251 22
1794348256 22
1794348261 22
1794348266 22
1794348271 22
1794348276 22
1794348282 22
1794348287 22
1794348292 35
1794348297 35
1794348302 22
1794348307 22
1794348312 22
1794348317 22
1794348322 22
1794348327 22
```
</details>

---

