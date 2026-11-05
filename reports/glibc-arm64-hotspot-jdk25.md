---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 12:01:06 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (3 unique values: 46-51 cores)</summary>

```
1793897792 47
1793897797 47
1793897802 47
1793897807 47
1793897812 47
1793897817 47
1793897822 47
1793897827 47
1793897832 47
1793897837 47
1793897842 47
1793897847 47
1793897852 47
1793897857 51
1793897862 51
1793897867 51
1793897872 51
1793897877 46
1793897882 46
1793897887 46
```
</details>

---

