---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 05:52:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (3 unique values: 31-40 cores)</summary>

```
1790243073 31
1790243078 31
1790243083 31
1790243088 31
1790243093 31
1790243098 36
1790243103 36
1790243108 36
1790243113 36
1790243118 36
1790243123 36
1790243128 36
1790243133 36
1790243138 36
1790243143 36
1790243148 36
1790243153 36
1790243158 36
1790243163 36
1790243168 36
```
</details>

---

