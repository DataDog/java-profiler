---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-27 09:00:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 20.00/sec |
| Health Score | 1250% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 26.50/sec |
| Health Score | 1656% |
| Threads | 11 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 20-32 cores)</summary>

```
1769514148 20
1769514153 20
1769514158 20
1769514163 20
1769514168 20
1769514173 20
1769514178 20
1769514183 20
1769514188 20
1769514193 20
1769514198 20
1769514203 22
1769514208 22
1769514213 22
1769514218 22
1769514223 22
1769514228 22
1769514233 22
1769514238 22
1769514243 22
```
</details>

---

