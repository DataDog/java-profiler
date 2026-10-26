---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 08:57:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (6 unique values: 42-47 cores)</summary>

```
1793019113 43
1793019118 43
1793019123 43
1793019128 43
1793019133 43
1793019138 42
1793019143 42
1793019148 42
1793019153 42
1793019158 47
1793019163 47
1793019168 47
1793019173 47
1793019178 45
1793019183 45
1793019188 45
1793019193 45
1793019198 46
1793019203 46
1793019208 46
```
</details>

---

