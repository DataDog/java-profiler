---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-01 15:37:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788291172 48
1788291177 48
1788291182 48
1788291187 48
1788291192 48
1788291197 48
1788291202 48
1788291207 43
1788291212 43
1788291217 43
1788291222 43
1788291227 43
1788291232 43
1788291237 43
1788291242 43
1788291247 43
1788291252 43
1788291257 43
1788291262 43
1788291267 43
```
</details>

---

