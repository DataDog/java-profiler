---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 09:38:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 78-88 cores)</summary>

```
1793367172 78
1793367177 78
1793367182 80
1793367187 80
1793367192 80
1793367197 80
1793367202 80
1793367207 80
1793367213 80
1793367218 80
1793367223 80
1793367228 80
1793367233 80
1793367238 80
1793367243 80
1793367248 80
1793367253 88
1793367258 88
1793367263 88
1793367268 88
```
</details>

---

