---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-27 09:00:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 16.00/sec |
| Health Score | 1000% |
| Threads | 10 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 26.43/sec |
| Health Score | 1652% |
| Threads | 12 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1769514143 46
1769514148 46
1769514153 46
1769514158 46
1769514163 46
1769514168 46
1769514173 41
1769514178 41
1769514183 41
1769514188 41
1769514193 41
1769514198 41
1769514203 41
1769514208 41
1769514213 41
1769514218 41
1769514223 41
1769514228 41
1769514233 41
1769514238 41
```
</details>

---

