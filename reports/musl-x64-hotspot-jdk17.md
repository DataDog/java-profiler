---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 16:58:43 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 10 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 67-79 cores)</summary>

```
1792616008 79
1792616013 79
1792616018 79
1792616023 67
1792616028 67
1792616033 67
1792616038 67
1792616043 67
1792616048 69
1792616053 69
1792616058 69
1792616063 69
1792616068 69
1792616073 69
1792616078 69
1792616083 69
1792616088 69
1792616093 69
1792616098 69
1792616103 69
```
</details>

---

