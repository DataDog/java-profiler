---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 11:59:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 6-18 cores)</summary>

```
1790265009 6
1790265014 6
1790265019 6
1790265024 6
1790265029 6
1790265034 6
1790265039 6
1790265044 6
1790265049 6
1790265054 6
1790265059 6
1790265064 18
1790265069 18
1790265074 18
1790265079 18
1790265084 18
1790265089 18
1790265094 18
1790265099 18
1790265104 18
```
</details>

---

