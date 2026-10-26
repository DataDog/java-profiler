---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 06:58:46 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793011797 32
1793011802 32
1793011807 32
1793011812 32
1793011817 32
1793011822 32
1793011827 32
1793011832 32
1793011837 32
1793011842 32
1793011847 32
1793011852 32
1793011857 32
1793011862 32
1793011867 32
1793011872 32
1793011877 32
1793011882 32
1793011887 32
1793011892 32
```
</details>

---

