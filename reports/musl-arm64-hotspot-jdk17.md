---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-06 05:37:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 15 |
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
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 10 |
| Allocations | 107 |

<details>
<summary>CPU Timeline (2 unique values: 15-35 cores)</summary>

```
1791279088 35
1791279093 35
1791279098 35
1791279103 35
1791279108 35
1791279113 15
1791279118 15
1791279123 15
1791279128 15
1791279133 15
1791279138 15
1791279143 15
1791279148 15
1791279153 15
1791279158 15
1791279163 15
1791279168 15
1791279173 15
1791279178 15
1791279183 15
```
</details>

---

