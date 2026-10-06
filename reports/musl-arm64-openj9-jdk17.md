---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-06 05:37:39 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 18-24 cores)</summary>

```
1791279077 24
1791279082 24
1791279087 24
1791279092 24
1791279097 24
1791279102 18
1791279107 18
1791279112 18
1791279117 18
1791279122 18
1791279127 18
1791279132 18
1791279137 18
1791279142 18
1791279147 19
1791279152 19
1791279157 19
1791279162 19
1791279167 19
1791279172 19
```
</details>

---

