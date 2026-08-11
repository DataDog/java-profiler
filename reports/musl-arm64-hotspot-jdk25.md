---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 12:25:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 12 |
| Allocations | 165 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1786465133 27
1786465138 27
1786465143 27
1786465148 27
1786465153 27
1786465158 27
1786465163 27
1786465168 28
1786465173 28
1786465178 28
1786465183 28
1786465188 28
1786465193 28
1786465198 28
1786465203 28
1786465208 27
1786465213 27
1786465218 27
1786465223 27
1786465228 27
```
</details>

---

