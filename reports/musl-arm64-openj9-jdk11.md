---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:08:51 EST

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 10 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 15-51 cores)</summary>

```
1794999757 15
1794999762 15
1794999767 15
1794999772 15
1794999777 15
1794999782 15
1794999787 15
1794999792 51
1794999797 51
1794999802 51
1794999807 51
1794999812 51
1794999817 51
1794999822 51
1794999827 51
1794999832 51
1794999837 51
1794999842 51
1794999847 51
1794999852 51
```
</details>

---

