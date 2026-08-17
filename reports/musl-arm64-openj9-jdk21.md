---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 10:37:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1786977204 47
1786977209 47
1786977214 47
1786977219 47
1786977224 42
1786977229 42
1786977234 42
1786977239 42
1786977244 43
1786977249 43
1786977254 43
1786977259 43
1786977264 43
1786977269 43
1786977274 48
1786977279 48
1786977284 48
1786977289 48
1786977294 48
1786977299 43
```
</details>

---

