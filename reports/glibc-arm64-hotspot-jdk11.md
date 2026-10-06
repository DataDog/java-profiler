---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 05:37:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 8 |
| Allocations | 191 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 10 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 50-51 cores)</summary>

```
1791279072 51
1791279077 51
1791279082 51
1791279087 51
1791279092 51
1791279097 51
1791279102 51
1791279107 50
1791279113 50
1791279118 50
1791279123 50
1791279128 50
1791279133 50
1791279138 50
1791279143 50
1791279148 50
1791279153 50
1791279158 51
1791279163 51
1791279168 51
```
</details>

---

