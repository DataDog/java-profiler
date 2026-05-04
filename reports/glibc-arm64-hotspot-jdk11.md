---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-03 21:22:22 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857132 64
1777857137 64
1777857142 64
1777857147 64
1777857152 64
1777857157 64
1777857162 64
1777857167 64
1777857172 64
1777857177 64
1777857182 64
1777857187 64
1777857192 64
1777857197 64
1777857202 64
1777857207 64
1777857212 64
1777857217 64
1777857222 64
1777857227 64
```
</details>

---

