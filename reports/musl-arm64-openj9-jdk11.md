---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 09:38:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 43-46 cores)</summary>

```
1793367147 43
1793367152 43
1793367157 43
1793367162 43
1793367167 43
1793367172 43
1793367177 43
1793367182 43
1793367187 43
1793367192 43
1793367197 43
1793367202 43
1793367207 43
1793367212 43
1793367218 43
1793367223 43
1793367228 43
1793367233 43
1793367238 43
1793367243 43
```
</details>

---

