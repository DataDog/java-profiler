---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-23 19:01:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1792796136 41
1792796141 41
1792796146 41
1792796151 41
1792796156 41
1792796161 41
1792796166 41
1792796171 41
1792796176 41
1792796181 46
1792796186 46
1792796191 46
1792796196 46
1792796201 46
1792796206 46
1792796211 46
1792796216 46
1792796221 46
1792796226 46
1792796231 46
```
</details>

---

