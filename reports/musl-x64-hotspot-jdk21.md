---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 09:30:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 16-24 cores)</summary>

```
1792157132 22
1792157137 22
1792157142 22
1792157147 22
1792157152 22
1792157157 22
1792157162 22
1792157167 22
1792157172 22
1792157177 22
1792157183 22
1792157188 22
1792157193 22
1792157198 24
1792157203 24
1792157208 24
1792157213 24
1792157218 24
1792157223 24
1792157228 24
```
</details>

---

