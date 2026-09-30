---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 10:59:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 88 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790780108 32
1790780113 32
1790780118 32
1790780123 32
1790780128 32
1790780133 32
1790780138 32
1790780143 32
1790780148 32
1790780153 32
1790780158 32
1790780163 32
1790780168 32
1790780173 32
1790780178 32
1790780183 32
1790780188 32
1790780193 32
1790780198 32
1790780203 32
```
</details>

---

