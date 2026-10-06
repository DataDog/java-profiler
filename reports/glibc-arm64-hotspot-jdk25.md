---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-06 05:37:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 11 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (2 unique values: 50-51 cores)</summary>

```
1791279091 51
1791279096 51
1791279101 51
1791279106 50
1791279111 50
1791279116 50
1791279121 50
1791279126 50
1791279131 50
1791279136 50
1791279142 50
1791279147 50
1791279152 50
1791279157 50
1791279162 51
1791279167 51
1791279172 51
1791279177 51
1791279182 51
1791279187 51
```
</details>

---

