---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 12:39:25 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 9 |
| Allocations | 178 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 14 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 26-43 cores)</summary>

```
1792686801 31
1792686806 31
1792686811 31
1792686816 31
1792686821 31
1792686826 31
1792686831 31
1792686836 31
1792686841 26
1792686846 26
1792686851 26
1792686856 26
1792686862 26
1792686867 26
1792686872 26
1792686877 26
1792686882 26
1792686887 26
1792686892 26
1792686897 26
```
</details>

---

