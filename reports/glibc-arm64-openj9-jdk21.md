---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-13 08:37:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 9 |
| Allocations | 203 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 12 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791894782 48
1791894787 48
1791894792 48
1791894797 48
1791894802 48
1791894807 48
1791894812 48
1791894817 48
1791894822 48
1791894827 43
1791894832 43
1791894837 43
1791894842 43
1791894847 43
1791894852 43
1791894857 43
1791894862 43
1791894867 43
1791894872 43
1791894877 48
```
</details>

---

